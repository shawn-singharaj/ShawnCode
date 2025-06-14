/*
Add an event handler for the submit event on the form with id "orderForm" in
    the file "order.html.
This event handler must:
1. Prevent submission of the form (which is the default action for the submit
    event on a form).
2. Get the values of the 2 input elements in the form. The value of an input
    element in a form is available as the attribute "value" of the element.
3. Append a new row to the table with the id "orderTable" in the file 
    "order.html." This row must contain the values entered by the user in the 2 input elements.
*/

document.addEventListener('DOMContentLoaded', function(){
    let orderForm = document.getElementById('orderForm');

    orderForm.addEventListener('submit', function(event){

        event.preventDefault();

        let company = document.getElementById('company').value;
        let quantity = document.getElementById('quantity').value;

        let tableBody = document.getElementById('tbody');
        let tr = document.createElement('tr');
        tableBody.appendChild(tr);

        let td1 = document.createElement('td');
        let td2 = document.createElement('td');
        
        td1.textContent = company;
        td2.textContent = quantity;

        tr.appendChild(td1);
        tr.appendChild(td2);

    });
});