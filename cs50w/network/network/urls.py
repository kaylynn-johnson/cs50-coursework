
from django.urls import path

from . import views

urlpatterns = [
    path("", views.index, name="index"),
    path("login", views.login_view, name="login"),
    path("logout", views.logout_view, name="logout"),
    path("register", views.register, name="register"),
    path("profile/<str:username>", views.show_profile, name="profile"),

    #API Routes
    path("post", views.create_post, name="create"),
    path("post/<int:post_id>", views.edit_post, name="edit"),
    path("post/<int:post_id>/like", views.like_post, name="like"),
    path("profile/<str:username>/follow", views.follow_user, name="follow")
]
