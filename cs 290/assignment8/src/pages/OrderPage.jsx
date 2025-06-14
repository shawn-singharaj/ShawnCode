import OrderTable from '../components/OrderTable';

function OrderPage(){

    return(
        <> 
            <h2>Order Your Groceries</h2>
            <p>Select the quantity of items you want to buy:</p>
            <OrderTable />            
        </>
    );
}

export default OrderPage;