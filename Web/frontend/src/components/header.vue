<template>
    <div id="header-bar">
        <md-toolbar class="md-transparent" id="md-a">
            
            <router-link :to="{path : '/'}" id="header_title">DOOR</router-link>

            <md-tabs class="md-transparent" md-alignment="centered">
                <md-tab id="tab-home" :to="{path: '/'}" md-icon="home"></md-tab>
                <md-tab id="tab-pages" :to="{path: '/setting'}" md-icon="settings"></md-tab>
            </md-tabs>
            
        </md-toolbar>
        

    </div>
</template>

<script>
export default {
  name: 'headerBar',

  data: () => ({

  }),
  created () {
    if (this.$session.exists()) {
      this.beforeLogin=false
      this.userName=this.$session.getAll().username;
      
    }
  },
  components: {
  },
  methods: {

  }
}

</script>

<style>
    .tab-list{
        color : white;
    }

    #md-a{
        background-color : blue;
    }

    #header_title {
        text-decoration:none;
        color : white;
        font-size : 23px;
    }
</style>

