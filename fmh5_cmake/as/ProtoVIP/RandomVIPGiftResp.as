package com.sanguo.game.server.connectlogic.common.message.ProtoVIP
{
	import laya.utils.Byte;
	public class RandomVIPGiftResp
	{
		public static const PROTO:String = "ProtoVIP.RandomVIPGiftResp";
		public var package_root:*;
		public  var message:*;
		public var item:Vector.<VIPGiftCPP>;
		public function RandomVIPGiftResp(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			item = new Vector.<VIPGiftCPP>();
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.item = [];
			for(var i:int = 0;i < this.item.length;i++)
			{
				serializeObj.item.push(this.item[i].serialize());
			}
			return serializeObj;
		}
		public function unserialize(msgObj:*):RandomVIPGiftResp
		{
			item = new Vector.<VIPGiftCPP>();
			for(var i:int = 0;i < msgObj.item.length;i++)
			{
				this.item.push(new VIPGiftCPP(package_root).unserialize(msgObj.item[i]));
			}
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):RandomVIPGiftResp
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}