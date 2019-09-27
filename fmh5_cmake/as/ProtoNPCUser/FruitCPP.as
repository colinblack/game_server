package com.sanguo.game.server.connectlogic.common.message.ProtoNPCUser
{
	import laya.utils.Byte;
	public class FruitCPP
	{
		public static const PROTO:String = "ProtoNPCUser.FruitCPP";
		public var package_root:*;
		public  var message:*;
		public var ud:int;
		public var treeid:int;
		public var status:int;
		public var stage:int;
		public var fruitLeftNum:int;
		public var harvestTime:int;
		public var name:Byte;
		public var fig:Byte;
		public function FruitCPP(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			ud = undefined;
			treeid = undefined;
			status = undefined;
			stage = undefined;
			fruitLeftNum = undefined;
			harvestTime = undefined;
			name = undefined;
			fig = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.ud = this.ud;
			serializeObj.treeid = this.treeid;
			serializeObj.status = this.status;
			serializeObj.stage = this.stage;
			serializeObj.fruitLeftNum = this.fruitLeftNum;
			serializeObj.harvestTime = this.harvestTime;
			if(this.name!= undefined)
			{
				serializeObj.name = this.name.getUint8Array(0, this.name.length);
				this.name.pos = 0;
			}
			if(this.fig!= undefined)
			{
				serializeObj.fig = this.fig.getUint8Array(0, this.fig.length);
				this.fig.pos = 0;
			}
			return serializeObj;
		}
		public function unserialize(msgObj:*):FruitCPP
		{
			ud = undefined;
			treeid = undefined;
			status = undefined;
			stage = undefined;
			fruitLeftNum = undefined;
			harvestTime = undefined;
			name = undefined;
			fig = undefined;
			this.ud = msgObj.ud;
			this.treeid = msgObj.treeid;
			this.status = msgObj.status;
			this.stage = msgObj.stage;
			this.fruitLeftNum = msgObj.fruitLeftNum;
			this.harvestTime = msgObj.harvestTime;
			if(msgObj.hasOwnProperty("name"))
			{
				this.name = new Byte();
				this.name.writeArrayBuffer(msgObj.name);
				this.name.pos = 0;
			}
			if(msgObj.hasOwnProperty("fig"))
			{
				this.fig = new Byte();
				this.fig.writeArrayBuffer(msgObj.fig);
				this.fig.pos = 0;
			}
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):FruitCPP
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}