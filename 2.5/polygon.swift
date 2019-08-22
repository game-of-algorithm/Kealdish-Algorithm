/*
	简单多边形。给定平面上的 N 个点，用它们画出一个多边形。
*/

/*
	找到 y 坐标最小的点 p，在有多个最小 y 坐标的点时取 x 坐标最小者，
	然后将其他点按照以 p 为原点的幅角大小的顺序依次连接起来。
*/

import Foundation
import CoreGraphics
import UIKit

struct Point2D {
    var x: CGFloat
    var y: CGFloat
    
    func lessInX(_ r: Point2D) -> Bool {
        return x < r.x
    }
    
    func lessInY(_ r: Point2D) -> Bool {
        return y < r.y
    }
    
    func lessInZero(_ r: Point2D) -> Bool {
        return calDistance() < r.calDistance()
    }
    
    func calDistance() -> CGFloat {
        return sqrt(pow(abs(x), 2) + pow(abs(y), 2))
    }
    
    func drawLine(_ r: Point2D) -> Point2D {
        let path = UIBezierPath.init()
        path.move(to: self.toCGPoint())
        path.addLine(to: r.toCGPoint())
        return r
    }
    
    func toCGPoint() -> CGPoint {
        return CGPoint.init(x: x, y: y)
    }
    
    func calAngle() -> CGFloat {
        return y / x
    }
}


func buildPolygon(_ pointList: [Point2D]) {
    
    let minPoint = pointList.min {
        if $0.y == $1.y {
            return $0.x < $1.y
        }
        return $0.y < $1.y
    }
    
    if let minPoint = minPoint {
        
        var points = pointList.map {
            return Point2D.init(x: $0.x - minPoint.x, y: $0.y - minPoint.y)
        }
        
        points.sort {
            
            if $0.x == $1.x {
                return $0.y < $1.y
            }
            
            if $0.x <= 0 && $1.x >= 0 {
                return false
            }
            
            if $0.x >= 0 && $1.x <= 0 {
                return true
            }
            
            let angle1 = $0.calAngle()
            let angle2 = $1.calAngle()
            
            return  angle1 < 0 ? angle1 > angle2 : angle1 < angle2
        }
        
        var curPoint = minPoint
        for point in points {
            curPoint = curPoint.drawLine(Point2D.init(x: point.x + minPoint.x, y: point.y + minPoint.y))
        }
        
        _ = curPoint.drawLine(minPoint)
    }
    
}
