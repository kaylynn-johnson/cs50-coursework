import json
from django.contrib.auth import authenticate, login, logout
from django.db import IntegrityError
from django.http import HttpResponse, HttpResponseRedirect, JsonResponse
from django.shortcuts import render
from django.urls import reverse

from .models import User, Post, Likes, Followers


def index(request):
    return render(request, "network/index.html")


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
            return render(request, "network/login.html", {
                "message": "Invalid username and/or password."
            })
    else:
        return render(request, "network/login.html")


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
            return render(request, "network/register.html", {
                "message": "Passwords must match."
            })

        # Attempt to create new user
        try:
            user = User.objects.create_user(username, email, password)
            user.save()
        except IntegrityError:
            return render(request, "network/register.html", {
                "message": "Username already taken."
            })
        login(request, user)
        return HttpResponseRedirect(reverse("index"))
    else:
        return render(request, "network/register.html")


def create_post(request):
    """Create post for user"""

    # Must use POST to create a new post
    if request.method != "POST":
        return JsonResponse({"error": "POST request required."}, status=400)
    
    data = json.loads(request.body)
    content = data.get("content")
    if not content:
        # No content passed
        return JsonResponse({"error": "Post cannot be blank."}, status=400)
    
    # Determine author
    author = User.objects.get(id=request.id)

    # Create the Post object
    # Created at and Updated at should be added automatically
    post = Post(author=author, content=content)
    post.save()

    return JsonResponse({"message": "Post submitted successfully"}, status=201)


def edit_post(request, post_id):
    """Edit contents of post_id"""
    pass


def like_post(request, post_id):
    """Like/Unlike post_id"""
    pass


def show_profile(request, username):
    """Show the profile of username"""
    pass


def follow_user(request, username):
    """Follow/Unfollow username"""
    pass