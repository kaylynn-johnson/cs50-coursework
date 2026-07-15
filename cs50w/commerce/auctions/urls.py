from django.urls import path

from . import views

app_name = "auctions"
urlpatterns = [
    path("", views.index, name="index"),
    path("login", views.login_view, name="login"),
    path("logout", views.logout_view, name="logout"),
    path("register", views.register, name="register"),
    path("create/", views.create_listing, name="create"),
    path("<str:listing_id>", views.listing, name="listing"),
    path("<str:listing_id>/bid", views.place_bid, name="bid_path"),
    path("<str:listing_id>/comment", views.comment, name="comment"),
    path("wishlist/", views.add_to_wishlist, name="wishlist")
]
