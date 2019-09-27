package com.sanguo.game.server.connectlogic.common.message.ProtoAlliance
{
	import laya.utils.Byte;
	public class ReplyAcceptInviteBC
	{
		public static const PROTO:String = "ProtoAlliance.ReplyAcceptInviteBC";
		public var package_root:*;
		public  var message:*;
		public var uid:int;
		public var alliance:AcceptInviteResp;
		public function ReplyAcceptInviteBC(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			uid = undefined;
			alliance = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.uid = this.uid;
			if(this.alliance!= undefined)
			{
				serializeObj.alliance = this.alliance.serialize();
			}
			return serializeObj;
		}
		public function unserialize(msgObj:*):ReplyAcceptInviteBC
		{
			uid = undefined;
			alliance = undefined;
			this.uid = msgObj.uid;
			if(msgObj.hasOwnProperty("alliance"))
			{
				this.alliance = new AcceptInviteResp(package_root).unserialize(msgObj.alliance);
			}
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):ReplyAcceptInviteBC
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}