from django.contrib.auth.models import AbstractUser
from django.db import models
from datetime import date, time


class User(AbstractUser):
    pass


class Post(models.Model):
    author = models.ForeignKey(User, on_delete=models.CASCADE, related_name="posts")
    content = models.TextField()
    created_at = models.DateTimeField(auto_now_add=True)

    class Meta:
        ordering = ['-created_at']
    
    def __str__(self):
        return f"Post by {self.author.username} at {self.created_at}"
    

class Likes(models.Model):
    post = models.ForeignKey(Post, on_delete=models.CASCADE, related_name="likes")
    user = models.ForeignKey(User, on_delete=models.CASCADE)

    def __str__(self):
        return f"{self.user.username} likes post #{self.post.id}"
    

class Followers(models.Model):
    initiator = models.ForeignKey(User, on_delete=models.CASCADE, related_name="following")
    receiver = models.ForeignKey(User, on_delete=models.CASCADE, related_name="follower")

    def __str__(self):
        return f"{self.initiator.username} follows {self.receiver.username}"