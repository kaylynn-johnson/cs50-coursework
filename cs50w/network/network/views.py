import json
from django.contrib.auth import authenticate, login, logout
from django.db import IntegrityError
from django.http import HttpResponse, HttpResponseRedirect, JsonResponse
from django.shortcuts import render
from django.urls import reverse
from django.views.generic import ListView

from .models import User, Post, Likes, Followers


class PostListView(ListView):
    paginate_by = 10
    model = Post
    

def index(request):
    """All posts view"""

    # Gather all of the information about the posts
    posts = Post.objects.all()
    likes = posts.likes


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
    # Must use PUT to edit a post
    if request.method != "PUT":
        return JsonResponse({"error": "PUT request required"}, status=400)
    
    # Ensure new content was passed to the function
    data = json.loads(request.body)
    new_content = data.get("new_content")
    if not new_content:
        return JsonResponse({"error": "Post cannot be blank"}, status=400)
    
    # Find post object by id
    if not Post.objects.filter(id=post_id).exists():
        return JsonResponse({"error": "Post with that ID does not exist"}, status=400)
    
    post = Post.objects.get(id=post_id)

    # Ensure owner and user editting are the same person
    if post.author != request.user:
        return JsonResponse({"error": "Only the author of the post can edit it."}, status=400)
    
    post.content = new_content
    post.save()
    return JsonResponse({"message": "Post updated successfully"}, status=204)


def like_post(request, post_id):
    """Like/Unlike post_id"""
    pass


def show_profile(request, username):
    """Show the profile of username"""
    pass


def follow_user(request, username):
    """Follow/Unfollow username"""
    pass