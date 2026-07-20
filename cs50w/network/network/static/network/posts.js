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
    // Edit button has been clicked so hide the div and show the text area & save button
    document.querySelector('#original-content').style.display = 'none';
    document.querySelector('#edit-content').style.display = 'block';
    document.querySelector('#save-post-edit').style.display = 'block';

    // Add event listener to save button
    document.querySelector('#save-post-edit').addEventListener('click', () => {
        // Gateher new content
        const new_content = document.querySelector('#edit-content').value;

        // Make put request
        fetch(`/post/${post_id}`, {
            method: "PUT",
            body: JSON.stringify({
                new_content: new_content
            })
        })
        .then(response => response.json())
        .then(result => {
            if (result.error !== undefined) {
                // Give alert
                alert(`Error: ${result.error}`)
                // Set edit content back to original content
                document.querySelector('#edit-content').value = document.querySelector('#original-content').value;
            } else {
                // Set edit and original content to new_content
                document.querySelector('#original-content').value = new_content;
                document.querySelector('#edit-content').value = new_content;
            }
        });

        // Hide text area & save button and show div
        document.querySelector('#edit-content').style.display = 'none';
        document.querySelector('#save-post-edit').style.display = 'none';
        document.querySelector('#original-content').style.display = 'block';
    });

    
}


// Like post


