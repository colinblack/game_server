package com.sanguo.game.server.connectlogic.common.message.User
{
	import laya.utils.Byte;
	public class BuyMaterialReq
	{
		public static const PROTO:String = "User.BuyMaterialReq";
		public var package_root:*;
		public  var message:*;
		public var buyinfo:Vector.<BuyMaterialInfo>;
		public var seq:int;
		public function BuyMaterialReq(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			buyinfo = new Vector.<BuyMaterialInfo>();
			seq = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.buyinfo = [];
			for(var i:int = 0;i < this.buyinfo.length;i++)
			{
				serializeObj.buyinfo.push(this.buyinfo[i].serialize());
			}
			serializeObj.seq = this.seq;
			return serializeObj;
		}
		public function unserialize(msgObj:*):BuyMaterialReq
		{
			buyinfo = new Vector.<BuyMaterialInfo>();
			seq = undefined;
			for(var i:int = 0;i < msgObj.buyinfo.length;i++)
			{
				this.buyinfo.push(new BuyMaterialInfo(package_root).unserialize(msgObj.buyinfo[i]));
			}
			this.seq = msgObj.seq;
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):BuyMaterialReq
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}