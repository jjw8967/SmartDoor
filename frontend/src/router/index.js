import Vue from 'vue'
import Router from 'vue-router'
import Home from '../components/home'
import NotFound from '../components/404'
import Sett from '../components/setting'


Vue.use(Router);

export default new Router({
    // '#' tag를 없애줌.
    mode : "history",

    //router's list
    routes : [
        {
            path: '/',
            component: Home
        },
        {
            path: '/404',
            component: NotFound
        },
        {
            path: '/setting',
            component: Sett
        }
    ]
})
