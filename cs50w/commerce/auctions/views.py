from django.contrib.auth import authenticate, login, logout
from django.contrib.auth.decorators import login_required
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
            return HttpResponseRedirect(reverse("auctions:index"))
        else:
            return render(request, "auctions/login.html", {
                "message": "Invalid username and/or password."
            })
    else:
        return render(request, "auctions/login.html")


def logout_view(request):
    logout(request)
    return HttpResponseRedirect(reverse("auctions:index"))


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
        return HttpResponseRedirect(reverse("auctions:index"))
    else:
        return render(request, "auctions/register.html")


@login_required
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


@login_required
def place_bid(request, listing_id):
    if request.method == "POST":
        # user submitted the form for the bid
        form = NewBidForm(request.POST)
        if form.is_valid():
            # determine if bid is high enough
            listing = AuctionListing.objects.get(pk=listing_id)
            bids_all = listing.bids.all()
            if not bids_all:
                # no bids found so compare against starting price
                price_to_beat = listing.starting_price
            else:
                price_to_beat = bids_all.aggregate(max_price=models.Max('price'))['max_price']
            
            # check with what user put in
            if int(request.POST["price"]) > price_to_beat:
                new_bid = form.save(commit=False)
                new_bid.user = request.user
                new_bid.listing = listing
                new_bid.save()
            else:
                # show error
                return render(request, "auctions/error.html", {
                    "error": f"Bid for {listing.title} is not high enough",
                    "listing_id": listing_id
                })
    
    #user got here for GET
    return HttpResponseRedirect(reverse("auctions:listing", args=(listing_id,)))


@login_required
def close_bid(request, listing_id):
    if request.method == "POST":
        # owner hit the submit button
        listing = AuctionListing.objects.get(pk=listing_id)
        listing.active = False
        listing.save()

    return HttpResponseRedirect(reverse("auctions:listing", args=(listing_id,)))


@login_required
def listing(request, listing_id):
    # give all the auction listing information to the page
    # find appropriate price
    listing = AuctionListing.objects.get(pk=listing_id)
    bids_all = listing.bids.all()
    if not bids_all:
        # no bids
        price = listing.starting_price
        winning_bidder = None
    else:
        price = bids_all.aggregate(max_price=models.Max('price'))['max_price']
        winning_bidder = Bid.objects.get(listing=listing, price=price).user

    # determine if item is on wishlist
    on_wishlist = Wishlist.objects.filter(user=request.user, listing=listing).exists()

    # determine if owner of the listing
    owner = AuctionListing.objects.filter(pk=listing_id, owner=request.user).exists()

    # determine if logged in user is the same as winning_bidder
    print(winning_bidder)
    if winning_bidder == request.user:
        winner = True
    else:
        winner = False

    return render(request, "auctions/listing.html", {
        "listing_info": listing,
        "price": price,
        "owner": owner,
        "winner": winner,
        "bids": listing.bids.all(),
        "bid_form": NewBidForm(),
        "comments": listing.comments.all(),
        "comment_form": NewCommentForm(),
        "on_wishlist": on_wishlist
    })

@login_required
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

@login_required
def user_wishlist(request):
    # can get here by GET
    return render(request, "auctions/wishlist.html", {
        "user": request.user,
        "wishlist": Wishlist.objects.filter(user=request.user)
    })

@login_required
def add_to_wishlist(request, listing_id):
    if request.method == "POST":
        # no form needed for this as it is just a button
        wishlist_entry = Wishlist.objects.create(listing=AuctionListing.objects.get(pk=listing_id), user=request.user)
        wishlist_entry.save()

    return HttpResponseRedirect(reverse("auctions:wishlist"))

@login_required
def remove_from_wishlist(request, listing_id):
    if request.method == "POST":
        wishlist_entry = Wishlist.objects.filter(user=request.user, listing=AuctionListing.objects.get(pk=listing_id))
        wishlist_entry.delete()

    return HttpResponseRedirect(reverse("auctions:wishlist"))

@login_required
def overall_categories(request):
    CATEGORIES = ["Fashion", "Toys", "Electronics",  "Home", "Miscellaneous"]
    return render(request, "auctions/overall_categories.html", {
        "categories": CATEGORIES
    })

@login_required
def category_listing(request, category):
    CATEGORIES = {"Fashion": "FASH", "Toys": "TOYS", "Electronics": "ELEC",  "Home": "HOME", "Miscellaneous": "MISC"}
    listings = AuctionListing.objects.filter(category=CATEGORIES[category], active=True)

    return render(request, "auctions/category.html", {
        "listings": listings
    })