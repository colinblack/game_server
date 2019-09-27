package com.sanguo.game.server.connectlogic.common.message.ProtoKeeper
{
	import laya.utils.Byte;
	public class KeeperTask
	{
		public static const PROTO:String = "ProtoKeeper.KeeperTask";
		public var package_root:*;
		public  var message:*;
		public var id:int;
		public var need:int;
		public var finish:int;
		public var status:int;
		public function KeeperTask(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			id = undefined;
			need = undefined;
			finish = undefined;
			status = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.id = this.id;
			serializeObj.need = this.need;
			serializeObj.finish = this.finish;
			serializeObj.status = this.status;
			return serializeObj;
		}
		public function unserialize(msgObj:*):KeeperTask
		{
			id = undefined;
			need = undefined;
			finish = undefined;
			status = undefined;
			this.id = msgObj.id;
			this.need = msgObj.need;
			this.finish = msgObj.finish;
			this.status = msgObj.status;
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):KeeperTask
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}