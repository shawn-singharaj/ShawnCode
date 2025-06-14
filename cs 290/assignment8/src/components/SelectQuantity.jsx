import { useState } from "react";
import { VscAdd, VscDash } from "react-icons/vsc";

function SelectQuantity({ initialQuantity, onQuantityChange }) {
    const [quantity, setQuantity] = useState(initialQuantity);

    const increment = () => {
        setQuantity(prevQuantity => {
            const newQuantity = prevQuantity < 10 ? prevQuantity + 1 : 10;
            onQuantityChange(newQuantity);
            return newQuantity;
        });
    };

    const decrement = () => {
        setQuantity(prevQuantity => {
            const newQuantity = prevQuantity > 0 ? prevQuantity - 1 : 0;
            onQuantityChange(newQuantity);
            return newQuantity;
        });
    };

    return (
        <div className="select-quantity">
            <button onClick={increment}><VscAdd /></button>
            <span>{quantity}</span>
            <button onClick={decrement}><VscDash /></button>
        </div>
    );
}


export default SelectQuantity;