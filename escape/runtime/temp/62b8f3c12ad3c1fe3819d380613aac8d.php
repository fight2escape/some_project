<?php if (!defined('THINK_PATH')) exit(); /*a:2:{s:75:"F:\Coding\wamp\www\escape\public/../application/index\view\index\about.html";i:1481608398;s:70:"F:\Coding\wamp\www\escape\public/../application/index\view\layout.html";i:1481589406;}*/ ?>
<!DOCTYPE html>
<html lang="en">
<head>
	<meta charset="UTF-8">
	<title>Fight2Escape-About</title>
	<link href="/static/handsome/img/f2e.ico" rel="shortcut icon" />
	<link rel="stylesheet" href="/static/handsome/css/home.css">
	<link rel="stylesheet" href="/static/handsome/css/article.css">
	<link rel="stylesheet" href="/static/handsome/css/raphaelicons.css">
	<link rel="stylesheet" href="/static/handsome/css/about.css">
</head>
<body>
	<div class="wrap">
		<section class="sidebar">
			<div class="sidebar__navbar">
				<a href="/index/index/home" class="navbar__a"><span class="ficon">S</span></a>
				<a href="#" class="navbar__a"><span class="ficon">U</span></a>
				<a href="/index/index/about" class="navbar__a  active"><span class="ficon">L</span></a>
			</div>
			<div class="sidebar__setting">
				<!-- <a href="#" class="setting__a"><span class="ficon">3</span></a> -->
				<!-- <a href="#" class="setting__a"><span class="ficon">a</span></a> -->
				<a href="/index/index/index" class="setting__a"><span class="ficon">v</span></a>
			</div>
		</section>
		<section class="detail">
	
			<section class="showpic showpic__about">
				<div class="showpic__summary">
					<h2>About Me</h2>
					<h3>以前没得选</h3>
					<h3>现在我想做个好人</h3>
					<p></p>
					<button><b class="ficon">Ã</b>up</button>

				</div>
			</section>

			
			<section class="main">

				<a href="#" class="mycard" >
					<div class="showimg"></div>
					<div class="mask">
						<div class="info">
							<h3>Fight 2 Escape</h3>
							<p>Shut Up!Just Do It!</p>
						</div>
					</div>
					<div class="border"></div>
				</a>
				<article class="about__article">
					<?php echo $res['content']; ?>
				</article>
				<footer>
					<b>&copy;</b>badwolf.cn  powerby fight2escape
				</footer>
			</section>

		</section>
	</div>
</body>
</html>	