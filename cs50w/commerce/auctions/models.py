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
    def __str__(self):
        return f"{self.username}"

class Bid(models.Model):
    price = models.IntegerField()
    user = models.ForeignKey(User, on_delete=models.CASCADE)

    def __str__(self):
        return f"{self.user} bid ${self.price}"

class Comment(models.Model):
    text = models.CharField(max_length=128)
    user = models.ForeignKey(User, on_delete=models.CASCADE)
    timestamp = models.DateTimeField(auto_now_add=True)
    
    def __str__(self):
        return f"{self.timestamp}: comment by {self.user}"

class AuctionListing(models.Model):
    #ASSUMPTION - last item in bids is the highest one
    bids = models.ManyToManyField(Bid, blank=True, related_name="bids")
    starting_price = models.FloatField()
    comments = models.ManyToManyField(Comment, blank=True, related_name="comments")
    title = models.CharField(max_length=100)
    description = models.TextField()
    url_image = models.URLField(blank=True)
    category = models.CharField(max_length=4, choices=CATEGORIES, default="MISC")
    active = models.BooleanField(default=True)
    owner = models.ForeignKey(User, on_delete=models.CASCADE)

    def __str__(self):
        return f"{self.title} ({self.owner})"

class Wishlist(models.Model):
    listings = models.ManyToManyField(AuctionListing, blank=True)
    user = models.OneToOneField(User, on_delete=models.CASCADE)

    def __str__(self):
        return f"{self.user}'s wishlist"