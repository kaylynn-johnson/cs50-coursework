from django.contrib import admin
from .models import User, Bid, Comment, AuctionListing, Wishlist

# Register your models here.
admin.site.register(User)
admin.site.register(Bid)
admin.site.register(Comment)
admin.site.register(AuctionListing)
admin.site.register(Wishlist)