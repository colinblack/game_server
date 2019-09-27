package com.sanguo.game.server.connectlogic.common.message.ProtoAlliance
{
	import laya.utils.Byte;
	public class ApplyJoinResp
	{
		public static const PROTO:String = "ProtoAlliance.ApplyJoinResp";
		public var package_root:*;
		public  var message:*;
		public var ret:int;
		public var apply:AllianceApplyCPP;
		public var member:AllianceMemberCPP;
		public var commons:CommonItemsCPP;
		public var alliance:AllianceCPP;
		public function ApplyJoinResp(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			ret = undefined;
			apply = undefined;
			member = undefined;
			commons = undefined;
			alliance = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			if(this.ret!= undefined)
			{
				serializeObj.ret = this.ret;
			}
			if(this.apply!= undefined)
			{
				serializeObj.apply = this.apply.serialize();
			}
			if(this.member!= undefined)
			{
				serializeObj.member = this.member.serialize();
			}
			if(this.commons!= undefined)
			{
				serializeObj.commons = this.commons.serialize();
			}
			if(this.alliance!= undefined)
			{
				serializeObj.alliance = this.alliance.serialize();
			}
			return serializeObj;
		}
		public function unserialize(msgObj:*):ApplyJoinResp
		{
			ret = undefined;
			apply = undefined;
			member = undefined;
			commons = undefined;
			alliance = undefined;
			if(msgObj.hasOwnProperty("ret"))
			{
				this.ret = msgObj.ret;
			}
			if(msgObj.hasOwnProperty("apply"))
			{
				this.apply = new AllianceApplyCPP(package_root).unserialize(msgObj.apply);
			}
			if(msgObj.hasOwnProperty("member"))
			{
				this.member = new AllianceMemberCPP(package_root).unserialize(msgObj.member);
			}
			if(msgObj.hasOwnProperty("commons"))
			{
				this.commons = new CommonItemsCPP(package_root).unserialize(msgObj.commons);
			}
			if(msgObj.hasOwnProperty("alliance"))
			{
				this.alliance = new AllianceCPP(package_root).unserialize(msgObj.alliance);
			}
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):ApplyJoinResp
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}