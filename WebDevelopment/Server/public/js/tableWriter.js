import data from './data.js';

// Don't change anything above this comment


// Feel free to define more functions if you want.


/**
 * Create and return an HTML table element using the value of variable 'data.'
 * The value of data is an array in which each element in turn is an array.
 * The top level array can have any number of elements greater than 1.
 * Each nested array will have the same number of elements.
 * This number will always be greater tha 0.
 * The HTML element created by this function will have as many columns
 * as the length of each nested array.
 * The elements in the first nested array (i.e., the array at index 0 in "data")
 * will be used to create <th> elements in the <thead> element of the table
 * The values of all other nested arrays will be used to create rows in the table,
 * one row for each of the other nested arrays, and using the value in a
 * nested array to create <td> elements in that row of the table.
 * @return HTML table element
 */
function createTableElement(){
    let tableElement = document.createElement('table');
    let tHead = document.createElement('thead');
    let tr = document.createElement('tr');

    tableElement.appendChild(tHead);
    tHead.appendChild(tr);    

    for(let i = 0; i < data[0].length; i++){
        let th = document.createElement('th');
        th.textContent = data[0][i];
        tr.appendChild(th);
    }

    let tbody = document.createElement('tbody');
    tableElement.appendChild(tbody);

    for(let i = 1; i < data.length; i++){
        let trbody = document.createElement('tr');
        tbody.appendChild(trbody);
        for(let j = 0; j < data[i].length; j++){
            let td = document.createElement('td');
            td.textContent = data[i][j];
            trbody.appendChild(td);
        }
    }
    
    // return the HTML table element
    return tableElement;
}

// Don't change anything below this comment
document.addEventListener('DOMContentLoaded', function() {
    document.getElementById('dynamicTable').appendChild(createTableElement())
})
