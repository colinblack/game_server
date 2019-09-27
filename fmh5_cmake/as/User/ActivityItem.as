package com.sanguo.game.server.connectlogic.common.message.User
{
	import laya.utils.Byte;
	public class ActivityItem
	{
		public static const PROTO:String = "User.ActivityItem";
		public var package_root:*;
		public  var message:*;
		public var id:int;
		public var bts:int;
		public var ets:int;
		public var ver:int;
		public function ActivityItem(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			id = undefined;
			bts = undefined;
			ets = undefined;
			ver = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.id = this.id;
			serializeObj.bts = this.bts;
			serializeObj.ets = this.ets;
			serializeObj.ver = this.ver;
			return serializeObj;
		}
		public function unserialize(msgObj:*):ActivityItem
		{
			id = undefined;
			bts = undefined;
			ets = undefined;
			ver = undefined;
			this.id = msgObj.id;
			this.bts = msgObj.bts;
			this.ets = msgObj.ets;
			this.ver = msgObj.ver;
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):ActivityItem
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}