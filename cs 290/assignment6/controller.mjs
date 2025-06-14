import express from 'express';
import * as model from './model.mjs';
const app = express();
const PORT = 3000;

app.use(express.json())

// Don't change or add anything above this line

function errorMessage(code){
    switch(code){
        case 400:
            return "Error: Invalid request";
        case 404:
            return "Error: Not found";
        default:
            return "Error";
    }
}

// POST
app.post("/orders", (req, res) => {
    const {company, quantity} = req.body;

    if(typeof(company) != "string" || company.length < 2 || typeof(quantity) != "number" || quantity < 1
    || quantity % 1 !== 0){
        res.status(400).send(errorMessage(400));
    }

    const order = model.createOrder(company, quantity);
    res.status(201).json(order);
})

// GET
app.get("/orders", (req, res) => {
    if(Object.keys(req.query).length === 0){
        res.status(200).json(model.returnOrders());
    }
    else{
        const company = req.query.company;
        res.status(200).json(model.returnQueryOrder(company));
    }

})

// GET ID
app.get("/orders/:id", (req, res) => {
    const order_id = req.params.id;
    
    const order = model.returnidOrder(order_id);

    if(order == null){
        res.status(404).send(errorMessage(404));
    }

    res.status(200).json(order);
})

// PUT
app.put("/orders/:id", (req, res) => {
    const order_id = req.params.id;
    const {quantity} = req.body;

    if(quantity < 1 || typeof(quantity) !== 'number'){
        res.status(400).send(errorMessage(400));
    }

    const order = model.returnidOrder(order_id);

    if(order == null){
        res.status(404).send(errorMessage(404));
    }

    const updateOrder = model.addOrder(quantity, order_id);
    res.status(200).json(updateOrder);
})

// DELETE
app.delete("/orders/:id", (req, res) => {
    const order_id = req.params.id;
    const order = model.returnidOrder(order_id);

    if(order == null){
        res.status(404).send(errorMessage(404));
    }

    res.status(204).send(model.deleteOrder(order_id));
})


// Don't change or add anything below this line
app.listen(PORT, () => {
  console.log(`Server listening on port ${PORT}...`);
});