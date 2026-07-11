from django.shortcuts import render
from django.http import HttpResponse
from datetime import datetime

now = datetime.now()
# Create your views here.
def index(request):
    return render(request, "newyear/index.html", {
        "newyear": now.month == 1 and now.day == 1
    })