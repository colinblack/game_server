package com.sanguo.game.server.connectlogic.common.message.ProtoFriendWorker
{
	import laya.utils.Byte;
	public class ThanksWorkerReq
	{
		public static const PROTO:String = "ProtoFriendWorker.ThanksWorkerReq";
		public var package_root:*;
		public  var message:*;
		public var workerUid:int;
		public function ThanksWorkerReq(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			workerUid = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.workerUid = this.workerUid;
			return serializeObj;
		}
		public function unserialize(msgObj:*):ThanksWorkerReq
		{
			workerUid = undefined;
			this.workerUid = msgObj.workerUid;
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):ThanksWorkerReq
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}