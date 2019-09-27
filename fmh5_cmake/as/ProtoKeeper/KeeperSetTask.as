package com.sanguo.game.server.connectlogic.common.message.ProtoKeeper
{
	import laya.utils.Byte;
	public class KeeperSetTask
	{
		public static const PROTO:String = "ProtoKeeper.KeeperSetTask";
		public var package_root:*;
		public  var message:*;
		public var keeperId:int;
		public var task:Vector.<KeeperTaskItem>;
		public function KeeperSetTask(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			keeperId = undefined;
			task = new Vector.<KeeperTaskItem>();
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.keeperId = this.keeperId;
			serializeObj.task = [];
			for(var i:int = 0;i < this.task.length;i++)
			{
				serializeObj.task.push(this.task[i].serialize());
			}
			return serializeObj;
		}
		public function unserialize(msgObj:*):KeeperSetTask
		{
			keeperId = undefined;
			task = new Vector.<KeeperTaskItem>();
			this.keeperId = msgObj.keeperId;
			for(var i:int = 0;i < msgObj.task.length;i++)
			{
				this.task.push(new KeeperTaskItem(package_root).unserialize(msgObj.task[i]));
			}
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):KeeperSetTask
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}