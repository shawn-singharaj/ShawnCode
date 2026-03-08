/**
 * Models a point in 2 dimensions
 */
class Point2D {
    /**
     * 
     * @param {number} x The x-coordinate of the point
     * @param {number} y The y-coordinate of the point
     */
    constructor(x, y) {
        this.x = x;
        this.y = y;
    }

    /**
     * 
     * @param {object} p An instance of the class Point2Dim
     * @returns The Euclidean distance between this point and p
     */
    distanceFrom(p) {
        return Math.sqrt(Math.pow(p.x-this.x, 2) + Math.pow(p.y-this.y, 2));
    }
}

export {Point2D}