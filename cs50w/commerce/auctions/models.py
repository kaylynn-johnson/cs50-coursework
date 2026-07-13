from django.contrib.auth.models import AbstractUser
from django.db import models


CATEGORIES = [
    ("FASH", "Fashion"),
    ("TOYS", "Toys"),
    ("ELEC", "Electrionics"),
    ("HOME", "Home"),
    ("MISC", "Miscellaneous")
]
class User(AbstractUser):
    pass

class Bid(models.Model):
    price = models.IntegerField()
    user = models.ForeignKey(User, on_delete=models.CASCADE)

class Comment(models.Model):
    text = models.CharField(max_length=128)
    user = models.ForeignKey(User, on_delete=models.CASCADE)
    timestamp = models.DateTimeField(auto_now_add=True)

class AuctionListing(models.Model):
    bids = models.ManyToManyField(Bid, blank=True)
    starting_price = models.FloatField()
    comments = models.ManyToManyField(Comment, blank=True)
    title = models.CharField(max_length=100)
    description = models.TextField()
    url_image = models.URLField(blank=True)
    category = models.CharField(max_length=4, choices=CATEGORIES, default="MISC")
    active = models.BooleanField(default=True)

class Wishlist(models.Model):
    listings = models.ManyToManyField(AuctionListing, blank=True)
    user = models.OneToOneField(User, on_delete=models.CASCADE)