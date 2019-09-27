package com.sanguo.game.server.connectlogic.common.message.ProtoNPCUser
{
	import laya.utils.Byte;
	public class ShippingBoxCPP
	{
		public static const PROTO:String = "ProtoNPCUser.ShippingBoxCPP";
		public var package_root:*;
		public  var message:*;
		public var boxid:int;
		public var propsid:int;
		public var count:int;
		public var aidStatus:int;
		public var status:int;
		public var coin:int;
		public var exp:int;
		public var fig:Byte;
		public var name:Byte;
		public function ShippingBoxCPP(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			boxid = undefined;
			propsid = undefined;
			count = undefined;
			aidStatus = undefined;
			status = undefined;
			coin = undefined;
			exp = undefined;
			fig = undefined;
			name = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.boxid = this.boxid;
			serializeObj.propsid = this.propsid;
			serializeObj.count = this.count;
			serializeObj.aidStatus = this.aidStatus;
			serializeObj.status = this.status;
			serializeObj.coin = this.coin;
			serializeObj.exp = this.exp;
			if(this.fig!= undefined)
			{
				serializeObj.fig = this.fig.getUint8Array(0, this.fig.length);
				this.fig.pos = 0;
			}
			if(this.name!= undefined)
			{
				serializeObj.name = this.name.getUint8Array(0, this.name.length);
				this.name.pos = 0;
			}
			return serializeObj;
		}
		public function unserialize(msgObj:*):ShippingBoxCPP
		{
			boxid = undefined;
			propsid = undefined;
			count = undefined;
			aidStatus = undefined;
			status = undefined;
			coin = undefined;
			exp = undefined;
			fig = undefined;
			name = undefined;
			this.boxid = msgObj.boxid;
			this.propsid = msgObj.propsid;
			this.count = msgObj.count;
			this.aidStatus = msgObj.aidStatus;
			this.status = msgObj.status;
			this.coin = msgObj.coin;
			this.exp = msgObj.exp;
			if(msgObj.hasOwnProperty("fig"))
			{
				this.fig = new Byte();
				this.fig.writeArrayBuffer(msgObj.fig);
				this.fig.pos = 0;
			}
			if(msgObj.hasOwnProperty("name"))
			{
				this.name = new Byte();
				this.name.writeArrayBuffer(msgObj.name);
				this.name.pos = 0;
			}
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):ShippingBoxCPP
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}