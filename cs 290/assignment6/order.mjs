import { uid } from 'uid';

/**
 * Models a stock order
 */
class Order {
    /**
     * 
     * @param {string} company 
     * @param {number} quantity Must be an integer
     */
    constructor(company, quantity) {
        this.company = company;
        this.quantity = quantity;
        this.id = uid(24);
        this.date = (new Date()).toJSON();
    }
}

export default Order;