package com.sanguo.game.server.connectlogic.common.message.ProtoTask
{
	import laya.utils.Byte;
	public class RewardTaskReq
	{
		public static const PROTO:String = "ProtoTask.RewardTaskReq";
		public var package_root:*;
		public  var message:*;
		public var id:int;
		public function RewardTaskReq(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			id = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.id = this.id;
			return serializeObj;
		}
		public function unserialize(msgObj:*):RewardTaskReq
		{
			id = undefined;
			this.id = msgObj.id;
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):RewardTaskReq
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}