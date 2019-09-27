package com.sanguo.game.server.connectlogic.common.message.ProtoFriendWorker
{
	import laya.utils.Byte;
	public class FriendWorkerCPP
	{
		public static const PROTO:String = "ProtoFriendWorker.FriendWorkerCPP";
		public var package_root:*;
		public  var message:*;
		public var workerUid:int;
		public var workerEndTs:int;
		public var workerSlotPos:int;
		public var workerInvitedTs:int;
		public function FriendWorkerCPP(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			workerUid = undefined;
			workerEndTs = undefined;
			workerSlotPos = undefined;
			workerInvitedTs = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.workerUid = this.workerUid;
			serializeObj.workerEndTs = this.workerEndTs;
			serializeObj.workerSlotPos = this.workerSlotPos;
			if(this.workerInvitedTs!= undefined)
			{
				serializeObj.workerInvitedTs = this.workerInvitedTs;
			}
			return serializeObj;
		}
		public function unserialize(msgObj:*):FriendWorkerCPP
		{
			workerUid = undefined;
			workerEndTs = undefined;
			workerSlotPos = undefined;
			workerInvitedTs = undefined;
			this.workerUid = msgObj.workerUid;
			this.workerEndTs = msgObj.workerEndTs;
			this.workerSlotPos = msgObj.workerSlotPos;
			if(msgObj.hasOwnProperty("workerInvitedTs"))
			{
				this.workerInvitedTs = msgObj.workerInvitedTs;
			}
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):FriendWorkerCPP
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}