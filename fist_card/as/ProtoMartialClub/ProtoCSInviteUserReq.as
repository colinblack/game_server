package com.sanguo.game.server.connectlogic.common.message.ProtoMartialClub
{
	import com.sanguo.game.server.ServerManager;
	import laya.utils.Byte;
	public class ProtoCSInviteUserReq
	{
		public static const PROTO:String = "ProtoMartialClub.ProtoCSInviteUserReq";
		public var package_root:*;
		public  var message:*;
		public var myUid:int;
		public var othUid:int;
		public var slot:int;
		public var martialGrade:int;
		public var myLevel:int;
		public var myFig:String;
		public var myName:String;
		public function ProtoCSInviteUserReq(root:*)
		{
			package_root = root;
			message = ServerManager.getProtoMsg(PROTO);
			myUid = undefined;
			othUid = undefined;
			slot = undefined;
			martialGrade = undefined;
			myLevel = undefined;
			myFig = undefined;
			myName = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.myUid = this.myUid;
			serializeObj.othUid = this.othUid;
			serializeObj.slot = this.slot;
			serializeObj.martialGrade = this.martialGrade;
			serializeObj.myLevel = this.myLevel;
			serializeObj.myFig = this.myFig;
			serializeObj.myName = this.myName;
			return serializeObj;
		}
		public function unserialize(msgObj:*):ProtoCSInviteUserReq
		{
			myUid = undefined;
			othUid = undefined;
			slot = undefined;
			martialGrade = undefined;
			myLevel = undefined;
			myFig = undefined;
			myName = undefined;
			this.myUid = msgObj.myUid;
			this.othUid = msgObj.othUid;
			this.slot = msgObj.slot;
			this.martialGrade = msgObj.martialGrade;
			this.myLevel = msgObj.myLevel;
			this.myFig = msgObj.myFig;
			this.myName = msgObj.myName;
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):ProtoCSInviteUserReq
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}