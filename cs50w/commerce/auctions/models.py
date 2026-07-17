from django.contrib.auth.models import AbstractUser
from django.db import models


CATEGORIES = [
    ("FASH", "Fashion"),
    ("TOYS", "Toys"),
    ("ELEC", "Electronics"),
    ("HOME", "Home"),
    ("MISC", "Miscellaneous")
]

class User(AbstractUser):
    def __str__(self):
        return f"{self.username}"

class AuctionListing(models.Model):
    starting_price = models.IntegerField()
    title = models.CharField(max_length=100)
    description = models.TextField()
    url_image = models.URLField(blank=True)
    category = models.CharField(max_length=4, choices=CATEGORIES, default="MISC")
    active = models.BooleanField(default=True)
    owner = models.ForeignKey(User, on_delete=models.CASCADE)

    def __str__(self):
        return f"{self.title} ({self.owner})"
    
class Bid(models.Model):
    price = models.IntegerField()
    user = models.ForeignKey(User, on_delete=models.CASCADE)
    listing = models.ForeignKey(AuctionListing, on_delete=models.CASCADE, related_name="bids")

    def __str__(self):
        return f"{self.user} bid ${self.price}"

class Comment(models.Model):
    text = models.CharField(max_length=128)
    user = models.ForeignKey(User, on_delete=models.CASCADE)
    listing = models.ForeignKey(AuctionListing, on_delete=models.CASCADE, related_name="comments")
    
    def __str__(self):
        return f"{self.timestamp}: comment by {self.user}"

class Wishlist(models.Model):
    listing = models.ForeignKey(AuctionListing, on_delete=models.CASCADE)
    user = models.ForeignKey(User, on_delete=models.CASCADE)

    def __str__(self):
        return f"{self.user}'s wishlist"