import orders from './data/orders.mjs';
import Order from './order.mjs';


/**
 * 
 * @param {string} company 
 * @param {number} quantity 
 * @returns 
 */
function createOrder(company, quantity){
    const order = new Order(company, quantity)
    orders.push(order)
    return order
}

function returnOrders(){
    return orders;
}

function returnQueryOrder(company){
    for(let i = 0; i < orders.length; i++){
        if(company == orders[i].company){
            return orders[i];
        }
    }
}

function returnidOrder(company_id){
    for(let i = 0; i < orders.length; i++){
        console.log(orders[i].id);
        if(company_id == orders[i].id){
            return orders[i];
        }
    }
    return null;
}

function addOrder(quantity, company_id){
    const company = returnidOrder(company_id);
    if(company){
        company.quantity = quantity;
    }
    return company;
}

function deleteOrder(company_id){
    for(let i = 0; i < orders.length; i++){
        if(company_id == orders[i].id){
            orders.splice(i, 1);
        }
    }    
}

// Don't change anything above this line



export {createOrder, returnOrders, returnQueryOrder, returnidOrder, addOrder, deleteOrder};