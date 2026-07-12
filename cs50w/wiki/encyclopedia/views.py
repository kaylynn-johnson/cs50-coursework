from django.shortcuts import render
import markdown2
import random as r
from . import util


def index(request):
    if request.method == "POST":
        query = request.POST.get('q')
        entry_contents = util.get_entry(query)
        if entry_contents:
            # exact match was returned, so render that page
            return render(request, 'encyclopedia/content_page.html', {
                "title": query,
                "html_content": markdown2.markdown(entry_contents)
            })
        
        # not an exact match
        all_entries = util.list_entries()
        all_matches = []
        for entry in all_entries:
            if query.lower() in entry.lower():
                all_matches.append(entry)
        if all_matches:
            # some matches were found
            return render(request, 'encyclopedia/search.html', {
                "entries": all_matches
            })
        else:
            # render error
            return render(request, 'encyclopedia/error.html', {
                "error": "404: No search results found"
            })
    return render(request, "encyclopedia/index.html", {
        "entries": util.list_entries()
    })

def entry(request, title):
    entry_contents = util.get_entry(title)
    #print(markdown2.markdown(entry_contents))
    if not entry_contents:
        # title doesn't exist
        return render(request, 'encyclopedia/error.html', {
            "error": "404: Title Not Found"
        })
    
    return render(request, 'encyclopedia/content_page.html', {
        "title": title,
        "html_content": markdown2.markdown(entry_contents)
    })

def create(request):
    return render(request, 'encyclopedia/create_page.html')

def publish(request):
    # check if title exists
    title = request.POST.get('title')
    print(title)
    
    action = request.POST.get('action')
    if action == "create":
        # got to this through the create page form
        entry_contents = util.get_entry(title)
        if entry_contents:
            # title already exists so throw error
            return render(request, 'encyclopedia/error.html', {
                "error": "403: Forbidden - Page with that title already exists"
            })
        
    markdown_contents = request.POST.get('markdown_contents')
    print(markdown_contents)
    util.save_entry(title, markdown_contents)

    # render that page now
    return render(request, 'encyclopedia/content_page.html', {
        "title": title,
        "html_content": markdown2.markdown(markdown_contents)
    })

 
def edit(request):
    entry = request.POST.get('entry')
    entry_contents = util.get_entry(entry)
    if not entry_contents:
        # for some reason couldn't find the file
        return render(request, 'encyclopedia/error.html', {
            "error": "503: Unable to find page to edit"
        })
    
    return render(request, 'encyclopedia/edit.html', {
        "title": entry,
        "markdown_contents": entry_contents
    })

def random(request):
    # get list of entries and find random index
    entries = util.list_entries()

    num_entries = len(entries) - 1
    random_entry_title = entries[r.randint(0, num_entries)]

    # get entry's information
    random_entry_content = util.get_entry(random_entry_title)
    if not random_entry_content:
        # for some reason couldn't find the file
        return render(request, 'encyclopedia/error.html', {
            "error": "503: Unable to display random page"
        })
    return render(request, 'encyclopedia/content_page.html', {
        "title": random_entry_title,
        "html_content": markdown2.markdown(random_entry_content)
    })