from django.urls import path

from . import views

urlpatterns = [
    path("", views.index, name="index"),
    path("wiki/<str:title>", views.entry, name="entry"),
    path("create/", views.create, name="create"),
    path("publish/", views.publish, name="publish"),
    path("edit/", views.edit, name='edit'),
    path("random/", views.random, name='random')
]
