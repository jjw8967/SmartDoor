<template>
    <div id="setting">
        <!--항상 상단에 떠있는 bar-->
        <header-bar></header-bar>
            <md-dialog-prompt
      :md-active.sync="active"
      v-model="value"
      md-title="추가하고 싶은 알림을 입력해주세요."
      md-input-maxlength="30"
      md-input-placeholder="Type your notice..."
      md-confirm-text="Done" 
      @md-confirm="onAdd"
      />

    <md-button class="md-primary md-raised" @click="active = true">Add</md-button>
    
    

    <div class="body">
      <list v-for="list in lists" :key="list" v-bind:set="1" v-bind:msg="list" ></list>
    </div>


       
    </div>
</template>

<script>
    import headerBar from './header.vue'
    import list from './list.vue'

    export default {
        name: 'setting',
        data:()=>{
            return{
                active: false,
                value: null,
                lists: [],
            }
        },
        created: function(){
            this.$http.get("http://localhost:8000/notice/get").then((data)=>{
                for(let i=0;i<data.data.length;i++){
                    this.lists.push(data.data[i].text)
                }
            })
        },
        components: {
            headerBar,
            list
        },
        methods:{
            onAdd:function(){
                this.$http.post("http://localhost:8000/notice/create",{"text":this.value}).then((data)=>{
                    console.log(data)
                    this.lists.push(this.value)
                })
            },
        }
    }
</script>
<style>
.body{
    text-align: center;
    padding-top:30px;
}
</style>
