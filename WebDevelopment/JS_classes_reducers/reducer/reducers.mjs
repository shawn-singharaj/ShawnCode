/*
* Don't change the declaration of this function.
*/
function reducer1(previousValue, currentValue){

    if(typeof(previousValue) !== 'number'){
        if(typeof(currentValue) !== 'number'){
            return 0;
        }
        return currentValue;
    }
    if((typeof(currentValue) !== 'number')){
        return previousValue;
    }
    // else if(typeof(previousValue) !== 'number'){
    //     return previousValue;
    // }

    return currentValue + previousValue;

};

/*
* Don't change the declaration of this function.
*/
function reducer2(previousValue, currentValue){

    if(typeof(currentValue) !== 'number' || typeof(previousValue) !== 'number') {
        throw new TypeError("uh oh, not a number");
    }

    return currentValue + previousValue;

};


// Don't add or change anything below this comment.
export { reducer1, reducer2 };