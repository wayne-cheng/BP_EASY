import tensorflow as tf

n_input = 2
n_hidden = 5
n_output = 1

w1 = tf.Variable(tf.random_uniform([n_input, n_hidden], -1, 1))#均匀分布随机数
b1 = tf.Variable(tf.zeros([n_hidden]))
w2 = tf.Variable(tf.random_uniform([n_hidden, n_output], -1, 1))
b2 = tf.Variable(tf.zeros([n_output]))

x = tf.placeholder(tf.float32, [None, n_input])

hidden = tf.nn.sigmoid(tf.add(tf.matmul(x, w1), b1))

y = tf.nn.sigmoid(tf.matmul(hidden, w2) + b2)

y_ = tf.placeholder(tf.float32, [None, n_output])

#cost loss error
error = 0.5 * tf.reduce_sum(tf.pow(tf.subtract(y_, y), 2.0))

train_step = tf.train.GradientDescentOptimizer(0.5).minimize(error)

init = tf.global_variables_initializer()

sess = tf.Session()
sess.run(init)

x_data = [[0, 0],
          [0, 1],
          [1, 0],
          [1, 1]]
y_data = [[0],
          [1],
          [1],
          [0]]
display_step = 100

for i in range(10000):
    sess.run(train_step, feed_dict={x: x_data, y_:y_data})
    if i % display_step == 0:
        print("error is %.9f" % sess.run(error, feed_dict={x: x_data, y_:y_data}))

print("x_data is ", x_data)
print("y is ", sess.run(y, feed_dict={x: x_data}))
