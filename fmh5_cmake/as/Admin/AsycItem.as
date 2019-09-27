package com.sanguo.game.server.connectlogic.common.message.Admin
{
	import laya.utils.Byte;
	public class AsycItem
	{
		public static const PROTO:String = "Admin.AsycItem";
		public var package_root:*;
		public  var message:*;
		public var uid:int;
		public var id:int;
		public var count:int;
		public function AsycItem(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			uid = undefined;
			id = undefined;
			count = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.uid = this.uid;
			serializeObj.id = this.id;
			serializeObj.count = this.count;
			return serializeObj;
		}
		public function unserialize(msgObj:*):AsycItem
		{
			uid = undefined;
			id = undefined;
			count = undefined;
			this.uid = msgObj.uid;
			this.id = msgObj.id;
			this.count = msgObj.count;
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):AsycItem
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}