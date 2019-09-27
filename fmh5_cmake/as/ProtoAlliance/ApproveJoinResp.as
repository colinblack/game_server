package com.sanguo.game.server.connectlogic.common.message.ProtoAlliance
{
	import laya.utils.Byte;
	public class ApproveJoinResp
	{
		public static const PROTO:String = "ProtoAlliance.ApproveJoinResp";
		public var package_root:*;
		public  var message:*;
		public var applyUid:int;
		public var operate:int;
		public var member:AllianceMemberCPP;
		public function ApproveJoinResp(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			applyUid = undefined;
			operate = undefined;
			member = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.applyUid = this.applyUid;
			serializeObj.operate = this.operate;
			if(this.member!= undefined)
			{
				serializeObj.member = this.member.serialize();
			}
			return serializeObj;
		}
		public function unserialize(msgObj:*):ApproveJoinResp
		{
			applyUid = undefined;
			operate = undefined;
			member = undefined;
			this.applyUid = msgObj.applyUid;
			this.operate = msgObj.operate;
			if(msgObj.hasOwnProperty("member"))
			{
				this.member = new AllianceMemberCPP(package_root).unserialize(msgObj.member);
			}
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):ApproveJoinResp
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}