package com.sanguo.game.server.connectlogic.common.message.Admin
{
	import laya.utils.Byte;
	public class AsycAdd
	{
		public static const PROTO:String = "Admin.AsycAdd";
		public var package_root:*;
		public  var message:*;
		public var item:Vector.<AsycItem>;
		public function AsycAdd(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			item = new Vector.<AsycItem>();
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
		public function unserialize(msgObj:*):AsycAdd
		{
			item = new Vector.<AsycItem>();
			for(var i:int = 0;i < msgObj.item.length;i++)
			{
				this.item.push(new AsycItem(package_root).unserialize(msgObj.item[i]));
			}
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):AsycAdd
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}