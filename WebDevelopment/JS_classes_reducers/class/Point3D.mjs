import {Point2D} from './Point2D.mjs';

class Point3D extends Point2D{

    constructor(x, y, z){
        super(x, y);
        this.z = z;
    }

    distanceFrom(p) {
    
        return Math.sqrt(Math.pow(p.x-this.x, 2) + Math.pow(p.y-this.y, 2) + Math.pow(p.z-this.z, 2));
    }
}

export {Point3D};