'use strict';

import {Point2D} from './Point2D.mjs';
import {Point3D} from './Point3D.mjs';

test('Test 1. instance variables of Point2D are correct', () => {
    const p = new Point2D(1, 2);
    expect(p.x).toBe(1);
    expect(p.y).toBe(2);
});

test('Test 2. Distance calculation is correct for Point2D', () => {
    const p1 = new Point2D(1, 2);
    const p2 = new Point2D(0, 0)
    const distance1 = p1.distanceFrom(p2);
    expect(distance1.toFixed(6)).toBe('2.236068');
    // Distance calculation must be symmetric
    const distance2 = p2.distanceFrom(p1);
    expect(distance1).toBe(distance2);
});

test('Test 3. Distance calculation is correct for Point2D', () => {
    const p1 = new Point2D(1, 2);
    const p2 = new Point2D(-1, 4)
    const distance1 = p1.distanceFrom(p2);
    expect(distance1.toFixed(6)).toBe('2.828427');
    // Distance calculation must be symmetric
    const distance2 = p2.distanceFrom(p1);
    expect(distance1).toBe(distance2);
});


test('Test 4. instance variables of Point3D are correct', () => {
    const p = new Point3D(1, 2, 3);
    expect(p.x).toBe(1);
    expect(p.y).toBe(2);
    expect(p.z).toBe(3);
});

test('Test 5. Distance calculation is correct for Point3D', () => {
    const p1 = new Point3D(1, 2, 3);
    const p2 = new Point3D(0, 0, 0)
    const distance1 = p1.distanceFrom(p2);
    expect(distance1.toFixed(5)).toBe('3.74166');
    // Distance calculation must be symmetric
    const distance2 = p2.distanceFrom(p1);
    expect(distance1).toBe(distance2);
});


test('Test 6. Distance calculation is correct for Point3D', () => {
    const p1 = new Point3D(1, 2, 3);
    const p2 = new Point3D(3, 4, -5);
    const distance1 = p1.distanceFrom(p2);
    expect(distance1.toFixed(5)).toBe('8.48528');
    // Distance calculation should be symmetric
    const distance2 = p2.distanceFrom(p1);
    expect(distance1).toBe(distance2);
});
