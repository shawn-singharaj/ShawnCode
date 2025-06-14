import OrderRow from './OrderRow';
import items from '../data/items';
import '../App.css';

function OrderTable(){

    return(
        <table className="order-table">
            <thead >
                <tr className="order-table">
                    <th className="order-table" colSpan={3}>Name Price Quantity</th>
                </tr>
            </thead>
            <tbody >
                <tr className="order-table">
                    <td className="order-table">
                    {items.map((items, index) => (
                    <OrderRow 
                        key={index}
                        name={items.name} 
                        price={items.price} 
                    />
                    ))}
                    </td>
 
                </tr>
            </tbody>          
        </table>
    );
}

export default OrderTable;