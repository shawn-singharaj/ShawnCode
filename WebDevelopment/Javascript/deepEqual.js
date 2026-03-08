'use strict';
// Don't add or change anything above this comment.

/*
* Don't change the declaration of this function.
*/
function deepEqual(val1, val2) {
    if(typeof(val1) != typeof(val2)){
        return false;
    }
    if(val1 === val2){
        return true;
    } 
    if(val1 === null || val2 === null){
        return false;
    }
    if(Array.isArray(val1) != Array.isArray(val2)){
        return false;
    }
    if(Array.isArray(val1) && Array.isArray(val2)){
        if(val1.length != val2.length){
            return false;
        }
        for(let i = 0; i < val1.length; i++){
            if (!deepEqual(val1[i], val2[i])) {
                return false;
            }
        }
        return true;
    }
    if((typeof(val1) == 'object' && typeof(val2) == 'object') && val1 != null){

       let key1 = Object.keys(val1);
       let key2 = Object.keys(val2);

       if(key1.length != key2.length){
        return false;
       }

       for(let i = 0; i < key1.length; i++){
        if(!key2.includes(key1[i])){
            return false;
        }
        if(!deepEqual(val1[key1[i]], val2[key1[i]])){
            return false;
        }
       }
       return true;
    }
   

    return false;

}

// Don't add or change anything below this comment.
module.exports = deepEqual;