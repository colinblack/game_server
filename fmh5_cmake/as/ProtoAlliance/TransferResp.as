package com.sanguo.game.server.connectlogic.common.message.ProtoAlliance
{
	import laya.utils.Byte;
	public class TransferResp
	{
		public static const PROTO:String = "ProtoAlliance.TransferResp";
		public var package_root:*;
		public  var message:*;
		public var myself:AllianceMemberCPP;
		public var other:AllianceMemberCPP;
		public var alliance:AllianceCPP;
		public function TransferResp(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			myself = undefined;
			other = undefined;
			alliance = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.myself = this.myself.serialize();
			serializeObj.other = this.other.serialize();
			serializeObj.alliance = this.alliance.serialize();
			return serializeObj;
		}
		public function unserialize(msgObj:*):TransferResp
		{
			myself = undefined;
			other = undefined;
			alliance = undefined;
			this.myself = new AllianceMemberCPP(package_root).unserialize(msgObj.myself);
			this.other = new AllianceMemberCPP(package_root).unserialize(msgObj.other);
			this.alliance = new AllianceCPP(package_root).unserialize(msgObj.alliance);
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):TransferResp
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}