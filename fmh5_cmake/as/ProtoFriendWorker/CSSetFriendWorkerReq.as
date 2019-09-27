package com.sanguo.game.server.connectlogic.common.message.ProtoFriendWorker
{
	import laya.utils.Byte;
	public class CSSetFriendWorkerReq
	{
		public static const PROTO:String = "ProtoFriendWorker.CSSetFriendWorkerReq";
		public var package_root:*;
		public  var message:*;
		public var othuid:int;
		public var myuid:int;
		public var propisid:int;
		public var sourceType:int;
		public var sourceFlag:int;
		public function CSSetFriendWorkerReq(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			othuid = undefined;
			myuid = undefined;
			propisid = undefined;
			sourceType = undefined;
			sourceFlag = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.othuid = this.othuid;
			serializeObj.myuid = this.myuid;
			serializeObj.propisid = this.propisid;
			serializeObj.sourceType = this.sourceType;
			serializeObj.sourceFlag = this.sourceFlag;
			return serializeObj;
		}
		public function unserialize(msgObj:*):CSSetFriendWorkerReq
		{
			othuid = undefined;
			myuid = undefined;
			propisid = undefined;
			sourceType = undefined;
			sourceFlag = undefined;
			this.othuid = msgObj.othuid;
			this.myuid = msgObj.myuid;
			this.propisid = msgObj.propisid;
			this.sourceType = msgObj.sourceType;
			this.sourceFlag = msgObj.sourceFlag;
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):CSSetFriendWorkerReq
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}