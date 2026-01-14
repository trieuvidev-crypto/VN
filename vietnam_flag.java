int step = 0;
PVector pen;
color red = color(218, 37, 29);
color yellow = color(255, 255, 0);
boolean drawingStar = false;

void setup() {
  size(600, 400);
  background(255);
  frameRate(60);
  pen = new PVector(100, 100);
}

void draw() {
  strokeWeight(3);
  stroke(0);
  
  if (step < 4) {
    PVector[] corners = {
      new PVector(100, 100),
      new PVector(500, 100),
      new PVector(500, 300),
      new PVector(100, 300)
    };
    PVector target = corners[step];
    pen = PVector.lerp(pen, target, 0.1);
    line(pen.x, pen.y, target.x, target.y);
    if (pen.dist(target) < 2) {
      pen = target.copy();
      step++;
    }
  } else if (step == 4) {
    noStroke();
    fill(red);
    rect(100, 100, 400, 200);
    step++;
  } else if (step == 5) {
    drawingStar = true;
    step++;
  } else if (drawingStar) {
    drawStar(200, 200, 30, 70, 5);
    drawingStar = false;
    step++;
  } else if (step == 6) {
    fill(yellow);
    drawStar(200, 200, 30, 70, 5);
    step++;
  }
}

void drawStar(float x, float y, float radius1, float radius2, int npoints) {
  float angle = TWO_PI / npoints;
  float halfAngle = angle / 2.0;
  beginShape();
  for (float a = 0; a < TWO_PI; a += angle) {
    float sx = x + cos(a) * radius2;
    float sy = y + sin(a) * radius2;
    vertex(sx, sy);
    sx = x + cos(a + halfAngle) * radius1;
    sy = y + sin(a + halfAngle) * radius1;
    vertex(sx, sy);
  }
  endShape(CLOSE);
}