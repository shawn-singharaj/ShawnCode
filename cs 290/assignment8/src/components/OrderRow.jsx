import SelectQuantity from './SelectQuantity';
import { useState } from 'react';
import '../App.css';


function OrderRow({name, price}){

    const [quantity, setQuantity] = useState(0);

    const handleQuantityChange = (newQuantity) => {
        setQuantity(newQuantity); 
    };

    return(
        <tr>
            <td className="order-table">{name}</td>
            <td className="order-table">{price}</td>
            <td ><SelectQuantity 
                initialQuantity={quantity}
                onQuantityChange={handleQuantityChange}
            />
            </td>
        </tr>
    );

}

export default OrderRow;