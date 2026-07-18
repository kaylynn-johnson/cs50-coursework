from django.urls import path

from . import views

app_name = "auctions"
urlpatterns = [
    path("", views.index, name="index"),
    path("login", views.login_view, name="login"),
    path("logout", views.logout_view, name="logout"),
    path("register", views.register, name="register"),
    path("create/", views.create_listing, name="create"),
    path("wishlist/", views.user_wishlist, name="wishlist"),
    path("listing/<str:listing_id>", views.listing, name="listing"),
    path("listing/<str:listing_id>/bid", views.place_bid, name="bid"),
    path("listing/<str:listing_id>/close_bid", views.close_bid, name="close_bid"),
    path("listing/<str:listing_id>/comment", views.comment, name="comment"),
    path("wishlist/<str:listing_id>/add_wishlist", views.add_to_wishlist, name="add_wishlist"),
    path("wishlist/<str:listing_id>/remove_wishlist", views.remove_from_wishlist, name="remove_wishlist"),
    path("categories/", views.overall_categories, name="categories"),
    path("categories/<str:category>", views.category_listing, name="category_listing")
]
