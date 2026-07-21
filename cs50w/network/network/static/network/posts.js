// JS related to the pages

document.addEventListener('DOMContentLoaded', function() {
    // Hide create post section
    document.querySelector('#create-post').style.display = 'none';

    // add event listener to create post button
    document.querySelector('#create-post-btn').addEventListener('click', create_post);

    // add event listeners to all of the edit buttons
    document.querySelectorAll('.edit-post').forEach(button => {
        button.onclick = function() {
            console.log(`Creating Event Listener to edit post ${this.dataset.id}`);
            edit_post(this.dataset.id);
        };
    });
});

// Fetch CSRF Token from meta tag in header
function getCsrfToken() {
    const metaTag = document.querySelector('meta[name="csrf-token"]');
    if (metaTag) {
        // Successfully found tag
        return metaTag.content;
    }
    throw new Error('CSRF token meta tag not found');
}

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
        headers: {
            'X-CSRFToken': getCsrfToken()
        },
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


    location.reload();
}

// Edit post
function edit_post(post_id) {
    // Edit button has been clicked so hide the div and show the text area & save button
    document.querySelector(`#original-content-${post_id}`).style.display = 'none';
    document.querySelector(`#edit-content-${post_id}`).style.display = 'block';
    document.querySelector(`#save-post-edit-${post_id}`).style.display = 'block';

    // Add event listener to save button
    document.querySelector(`#save-post-edit-${post_id}`).addEventListener('click', () => {
        // Gateher new content
        const new_content = document.querySelector(`#edit-content-${post_id}`).value;
        console.log(new_content);
        console.log(document.querySelector(`#original-content-${post_id}`).innerHTML);

        // Make put request
        fetch(`/post/${post_id}`, {
            method: "PUT",
            headers: {
                'X-CSRFToken': getCsrfToken()
            },
            body: JSON.stringify({
                new_content: new_content
            })
        })
        .then(response => response.json())
        .then(result => {
            console.log(result);
            if (result.error !== undefined) {
                // Give alert
                alert(`Error: ${result.error}`);
                // Set edit content back to original content
                document.querySelector(`#edit-content-${post_id}`).value = document.querySelector(`#original-content-${post_id}`).innerHTML;
            } else {
                // Set edit and original content to new_content
                console.log('No error found!');
                console.log(new_content);
                document.querySelector(`#original-content-${post_id}`).innerHTML = new_content;
                document.querySelector(`#edit-content-${post_id}`).value = new_content;
            }
        })
        .catch(error => {
            console.log(`Caught error of ${error}`);
        });

        console.log(document.querySelector(`#original-content-${post_id}`).innerHTML);

        // Hide text area & save button and show div
        document.querySelector(`#original-content-${post_id}`).style.display = 'block';
        document.querySelector(`#edit-content-${post_id}`).style.display = 'none';
        document.querySelector(`#save-post-edit-${post_id}`).style.display = 'none';
    });

    
}


// Like post


