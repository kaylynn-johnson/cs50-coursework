from django.contrib.auth import authenticate, login, logout
from django.db import IntegrityError, models
from django.http import HttpResponse, HttpResponseRedirect
from django.shortcuts import render
from django.urls import reverse
from django import forms

from .models import User, Bid, Comment, AuctionListing, Wishlist

class NewListingForm(forms.ModelForm):
    class Meta:
        model = AuctionListing
        fields = ['title', 'description', 'starting_price', 'url_image', 'category']

class NewBidForm(forms.ModelForm):
    class Meta:
        model = Bid
        fields = ['price']
    
class NewCommentForm(forms.ModelForm):
    class Meta:
        model = Comment
        fields = ['text']

def index(request):
    # determine all of the auction listings that are active
    return render(request, "auctions/index.html", {
        "active_listings": AuctionListing.objects.filter(active__exact=True).annotate(max_price=models.Max('bids__price'))
    })


def login_view(request):
    if request.method == "POST":

        # Attempt to sign user in
        username = request.POST["username"]
        password = request.POST["password"]
        user = authenticate(request, username=username, password=password)

        # Check if authentication successful
        if user is not None:
            login(request, user)
            return HttpResponseRedirect(reverse("index"))
        else:
            return render(request, "auctions/login.html", {
                "message": "Invalid username and/or password."
            })
    else:
        return render(request, "auctions/login.html")


def logout_view(request):
    logout(request)
    return HttpResponseRedirect(reverse("index"))


def register(request):
    if request.method == "POST":
        username = request.POST["username"]
        email = request.POST["email"]

        # Ensure password matches confirmation
        password = request.POST["password"]
        confirmation = request.POST["confirmation"]
        if password != confirmation:
            return render(request, "auctions/register.html", {
                "message": "Passwords must match."
            })

        # Attempt to create new user
        try:
            user = User.objects.create_user(username, email, password)
            user.save()
        except IntegrityError:
            return render(request, "auctions/register.html", {
                "message": "Username already taken."
            })
        login(request, user)
        return HttpResponseRedirect(reverse("index"))
    else:
        return render(request, "auctions/register.html")


def create_listing(request):
    if request.method == "POST":
        # user submitted the form for the listing
        form = NewListingForm(request.POST)
        if form.is_valid():
            new_listing = form.save(commit=False)
            new_listing.owner = request.user
            new_listing.save()
            # redirect to index
            return HttpResponseRedirect(reverse("auctions:index"))
        
        #form is not valid
        return render(request, "auctions/create.html", {
            "form": form
        })
    
    # user got here by GET
    return render(request, "auctions/create.html", {
        "form": NewListingForm()
    })


def place_bid(request, listing_id):
    if request.method == "POST":
        # user submitted the form for the bid
        form = NewBidForm(request.POST)
        if form.is_valid():
            # determine if bid is high enough
            bids_all = AuctionListing.objects.get(pk=listing_id).bids.all()
            if not bids_all:
                # no bids found so compare against starting price
                price_to_beat = AuctionListing.objects.get(pk=listing_id).starting_price
            else:
                price_to_beat = bids_all.aggregate(max_price=models.Max('price'))['max_price']
            
            # check with what user put in
            if int(request.POST["price"]) > price_to_beat:
                new_bid = form.save(commit=False)
                new_bid.user = request.user
                new_bid.listing = AuctionListing.objects.get(pk=listing_id)
                new_bid.save()
                error = ""
            else:
                # show error
                error = "Bid is not high enough"
    
    #user got here for GET
    return HttpResponseRedirect(reverse("auctions:listing", args=(listing_id,)))


def listing(request, listing_id):
    # give all the auction listing information to the page
    # find appropriate price
    bids_all = AuctionListing.objects.get(pk=listing_id).bids.all()
    if not bids_all:
        # no bids
        price = AuctionListing.objects.get(pk=listing_id).starting_price
    else:
        price = bids_all.aggregate(max_price=models.Max('price'))['max_price']
    return render(request, "auctions/listing.html", {
        "listing_info": AuctionListing.objects.get(pk=listing_id),
        "price": price,
        "bids": AuctionListing.objects.get(pk=listing_id).bids.all(),
        "bid_form": NewBidForm(),
        "error": "",
        "comments": AuctionListing.objects.get(pk=listing_id).comments.all(),
        "comment_form": NewCommentForm()
    })


def comment(request, listing_id):
    if request.method == "POST":
        # user submitted the form for the comment
        form = NewCommentForm(request.POST)
        if form.is_valid():
            new_comment = form.save(commit=False)
            new_comment.user = request.user
            new_comment.listing = AuctionListing.objects.get(pk=listing_id)
            new_comment.save()

    # redirect back to listing page
    return HttpResponseRedirect(reverse("auctions:listing", args=(listing_id,)))
        

def add_to_wishlist(request, listing_id):
    if request.method == "POST":
        # no form needed for this as it is just a button
        wishlist_entry = Wishlist.objects.create(listing=AuctionListing.objects.get(pk=listing_id), user=request.user)
        wishlist_entry.save()

    return render(request, "auctions/wishlist.html", {
        "wishlist": User.objects.get(pk=request.user.id).wishlist
    })