use std::{fs::File, io::Write};
use std::ops::{Add, Sub, Mul, Div};

/* Image */
type Color = (u8, u8, u8);

struct Image {
    width: usize,
    height: usize,
    pixels: Vec<u8>,
}

impl Image {
    const MAGIC_NUMBER: &str = "P6";
    const COLOR_MAX_VAL: u8 = 255;

    pub fn new(width: usize, height: usize) -> Image {
        Image {
            width,
            height,
            pixels: vec![u8::default(); width * height * 3],
        }
    }

    pub fn set_pixel_color(&mut self, x: usize, y: usize, (r, g, b): Color) {
        let index = self.width * y * 3 + x * 3;
        self.pixels[index] = r;
        self.pixels[index + 1] = g;
        self.pixels[index + 2] = b;
    }

    pub fn save(self, filename: &str) {
        let mut file = File::create(filename).unwrap();
        let meta = format!("{}\n{} {}\n{}\n", Self::MAGIC_NUMBER, self.width, self.height, Self::COLOR_MAX_VAL);
        file.write(meta.as_bytes()).map_err(|err| println!("{:?}", err)).ok();
        file.write(&self.pixels).map_err(|err| println!("{:?}", err)).ok();
    }
}


/* Complex */
#[derive(Clone, Copy)]
struct Complex {
    re: f64,
    im: f64,
}

impl Add for Complex {
    type Output = Self;

    fn add(self, rhs: Self) -> Self::Output {
        Self {
            re: self.re + rhs.re,
            im: self.im + rhs.im,
        }
    }
}

impl Sub for Complex {
    type Output = Self;

    fn sub(self, rhs: Self) -> Self::Output {
        Self {
            re: self.re - rhs.re,
            im: self.im - rhs.im,
        }
    }
}

impl Mul for Complex {
    type Output = Self;

    fn mul(self, rhs: Self) -> Self::Output {
        Self {
            re: self.re * rhs.re - self.im * rhs.im,
            im: self.re * rhs.im + self.im * rhs.re,
        }
    }
}

impl Div for Complex {
    type Output = Self;

    fn div(self, rhs: Self) -> Self::Output {
        let divider = rhs.re.powf(2.0) + rhs.im.powf(2.0);

        Self {
            re: (self.re * rhs.re + self.im * rhs.im) / divider,
            im: (self.im * rhs.re - self.re * rhs.im) / divider,
        }
    }
}

impl Complex {
    fn new(re: f64, im: f64) -> Complex {
        Complex { re, im }
    }

    fn square(self) -> Complex {
        Complex {
            re: self.re.powf(2.0) - self.im.powf(2.0),
            im: self.re * self.im * 2.0,
        }
    }

    fn abs(self) -> f64 {
        self.im.powf(2.0) + self.re.powf(2.0)
    }
}

/* Fractal */
struct Fractal {
    width: usize,
    height: usize,
}

impl Fractal {
    const MAX_ITER: usize = 256;

    fn mandlebrot(c: Complex) -> usize {
        let mut z = Complex::new(0.0, 0.0);
        for i in 0..Self::MAX_ITER {
            if z.abs() > 2.0 { return i };
            z = z.square() + c;
        }

        Self::MAX_ITER
    }

    pub fn img(self, re_start: f64, re_end: f64, im_start: f64, im_end: f64) -> Image {
        let mut image = Image::new(self.width, self.height);
        for x in 0..self.width {
            for y in 0..self.height {
                let re = re_start + (x as f64 / self.width as f64) * (re_end - re_start);
                let im = im_start + (y as f64 / self.height as f64) * (im_end - im_start);
                let c = Complex::new(re, im);
                let m = Self::mandlebrot(c);
                let color = Image::COLOR_MAX_VAL - (m * 255 / Self::MAX_ITER) as u8;
                image.set_pixel_color(x, y, (color, color, color));
            }
        }
        image
    }
}

fn main() {
    let f = Fractal {
        width: 800,
        height: 600,
    };

    let img = f.img(-2.0, 1.0, -1.0, 1.0);
    img.save("fractal.png");

}