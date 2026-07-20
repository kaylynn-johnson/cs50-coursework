// JS related to the pages

document.addEventListener('DOMContentLoaded', function() {
    // Hide create post section
    document.querySelector('#create-post').style.display = 'none';

    // add event listener to create post button
    document.querySelector('#create-post-btn').addEventListener('click', create_post);

    // add event listeners to all of the edit buttons
    document.querySelectorAll('.edit-post').forEach(button => {
        button.onclick = function() {
            edit_post(this.dataset.id);
        };
    });
})

// Create post
function create_post() {
    // open the div to create the post
    document.querySelector('#create-post').style.display = 'block';

    // add event listener to post button
    document.querySelector('#submit-post').addEventListener('click', submit_post);
}

function submit_post() {
    // grab content text
    const content = document.querySelector('#new-post-content').value;

    fetch('/post', {
        method: 'POST',
        body: JSON.stringify({
            content: content
        })
    })
    .then(response => response.json())
    .then(result => {
        if (result.error !== undefined) {
            // give alert
            alert(`Error: ${result.error}`);
        } else {
            console.log(result);
        }
    });
}

// Edit post
function edit_post(post_id) {
    
}


// Like post


