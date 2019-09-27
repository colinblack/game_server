package com.sanguo.game.server.connectlogic.common.message.User
{
	import laya.utils.Byte;
	public class Activity
	{
		public static const PROTO:String = "User.Activity";
		public var package_root:*;
		public  var message:*;
		public var act:Vector.<ActivityItem>;
		public function Activity(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			act = new Vector.<ActivityItem>();
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.act = [];
			for(var i:int = 0;i < this.act.length;i++)
			{
				serializeObj.act.push(this.act[i].serialize());
			}
			return serializeObj;
		}
		public function unserialize(msgObj:*):Activity
		{
			act = new Vector.<ActivityItem>();
			for(var i:int = 0;i < msgObj.act.length;i++)
			{
				this.act.push(new ActivityItem(package_root).unserialize(msgObj.act[i]));
			}
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):Activity
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}